<?php
class magic_form {
  private $form_id = null;
  private $form_elements;
  private $submit_function;
  private $action = null;
  private $classes = array();

  const inactivity_max_time = '24 hours';

  public function __construct() {
    if($this->form_id === null){
      $this->form_id = uniqid('magic_form_');
    }
    self::cleanup_expired_forms();
    //self::remove_other_forms($this->form_id);
  }

  public function __destruct() {
    $this->__save();
  }

  public function __save(){
    $_SESSION['magic_forms'][$this->form_id] = array(
      'created' => date("Y-m-d H:i:s"),
      'form' => serialize($this),
    );
  }

  static public function remove_other_forms($exception_id = null) {
    // Expire old magic forms
    if(isset($_SESSION)){
      if(isset($_SESSION['magic_forms'])){
        foreach ($_SESSION['magic_forms'] as $form_id => $form_container) {
          if($exception_id !== $form_id || $exception_id === null){
            self::_dispose_form($form_id);
          }
        }
      }
    }
  }

  static private function _dispose_form($form_id){
    $form_container = $_SESSION['magic_forms'][$form_id];
    watchdog(
      "magic_forms",
      "Removing magic form #@form_id, created at @date",
      array(
           '@form_id' => $form_id,
           '@date' => date("Y-m-d H:i:s", strtotime($form_container['created']))
      ),
      WATCHDOG_INFO
    );
    unset($_SESSION['magic_forms'][$form_id]);
  }

  static public function cleanup_expired_forms() {
    // Expire old magic forms
    if(isset($_SESSION)){
      if(isset($_SESSION['magic_forms'])){
        foreach ($_SESSION['magic_forms'] as $form_id => $form_container) {
          if (strtotime($form_container['created']) < strtotime(self::inactivity_max_time . " ago")) {
            self::_dispose_form($form_id);
          }
        }
        if(count($_SESSION['magic_forms']) >= MAGIC_FORMS_MAX_ACTIVE_FORMS){
          $forms_by_time = array();
          foreach ($_SESSION['magic_forms'] as $form_id => $form_container) {
            $forms_by_time[strtotime($form_container['created'])] = $form_id;
          }

          // Pop off the items to preserve.
          for($i=1; $i < 5; $i++){
            array_pop($forms_by_time);
          }

          foreach($forms_by_time as $form_id){
            self::_dispose_form($form_id);
          }
        }
      }
    }
  }

  public function add_field(magic_form_item $field) {
    $this->form_elements[$field->get_name()] = $field;
    $this->__save();
    return $this;
  }

  public function add_fields(){
    foreach(func_get_args() as $argument){
      $this->add_field($argument);
    }
  }

  /**
   * Get a named field.
   *
   * @param $name
   *
   * @return magic_form_field
   */
  public function get_field($name) {
    foreach ($this->form_elements as $element_name => $element) {
      if ($element_name == $name) {
        return $this->form_elements[$name];
      }
      if (get_class($element) == 'magic_form_group') {
        $sub_fields = $element->get_fields();
        if(count($sub_fields) > 0){
          foreach ($sub_fields as $sub_element_name => $sub_element) {
            if ($sub_element_name == $name) {
              return $sub_fields[$sub_element_name];
            }
          }
        }
      }
    }
    watchdog("Remedy Ticket form: Cannot find field: {$name}", "warning");
    return FALSE;
  }

  public function get_fields(){
    $fields = array();
    foreach ($this->form_elements as $element_name => $element) {
      if (get_class($element) == 'magic_form_group') {
        $sub_fields = $element->get_fields();
        if(count($sub_fields) > 0){
          foreach ($sub_fields as $sub_element_name => $sub_element) {
              $fields[$sub_element_name] = $sub_fields[$sub_element_name];
          }
        }
      }else{
        $fields[$element_name] = $element;
      }
    }
    if($_REQUEST['magic_form_id'] == $this->get_form_id()){
      foreach($_REQUEST as $key => $value){
        $field = new magic_form_field();
        $field->set_name($key);
        $field->set_value($value);
        $fields[$key] = $field;
      }
    }
    return $fields;
  }

  public function __toString() {
    $view = new StdClass();
    $view->form_rows = $this->form_elements;
    $view->action = $this->get_action();
    $view->form_id = $this->get_form_id();
    $view->classes = $this->get_classes();
    $this->__save();
    return magic_forms_template_view("form.phtml", $view);
  }

  public function get_action() {
    if($this->action){
      return $this->action;
    }else{
      return $_SERVER['REQUEST_URI'];
    }
  }

  public function set_action($target){
    $this->action = $target;
    return $this;
  }

  public function submit($submit_function) {
    $this->submit_function = new magic_serialisable_closure($submit_function);
    return $this;
  }

  public function do_submit() {
    $this->populate_with_request();
    $this->submit_function->__invoke($this);
  }

  private function populate_with_request() {
    foreach ($_REQUEST as $key => $value) {
      switch ($key) {
        case 'magic_form_id':
          // Do nothing;
          break;

        default:
          $item = $this->get_field($key);
          if ($item) {
            $item->set_value($value);
          }
      }
    }
  }

  public function get_form_id() {
    return $this->form_id;
  }

  public static function process($magic_form_id) {
    if (!isset($_SESSION['magic_forms'][$magic_form_id])) {
      drupal_set_message("Uhoh... The form expired after " . self::inactivity_max_time . "! Please try again.", "error");
      header("Location: {$_SERVER['HTTP_REFERER']}");
      exit;
    } else {
      $form = unserialize($_SESSION['magic_forms'][$magic_form_id]['form']);
      $form->do_submit();
    }
  }

  public function add_error($message, $element = null){
    drupal_set_message($message, 'error');

    $field = $this->get_field($element);
    if($field instanceof magic_form_field){
      $field->add_error($message);
    }
  }

  public function add_default($value, $element = null){
    $field = $this->get_field($element);
    if($field instanceof magic_form_field){
      $field->set_value($value);
    }
    return $this;
  }

  public function set_defaults($defaults){
    foreach($defaults as $element_name => $value){
      $this->add_default($value, $element_name);
    }
    return $this;
  }

  public function add_class($class){
    $this->classes[] = $class;
    return $this;
  }

  public function get_classes(){
    return $this->classes;
  }
}