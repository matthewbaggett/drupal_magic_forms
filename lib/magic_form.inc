<?php
class magic_form extends active_record{
  protected $_table = "magic_forms";

  const MAGIC_FORM_RENDER_MODE_VIEW = 'view';
  const MAGIC_FORM_RENDER_MODE_EDIT = 'edit';

  public $magic_form_id;
  public $form_id = null;
  public $created;
  public $uid;
  public $form_elements;
  public $submit_function;
  public $submit_destination = null;
  public $render_mode = self::MAGIC_FORM_RENDER_MODE_EDIT;
  public $action = null;
  public $classes = array();
  public $form_name = null;
  public $fields_to_omit = array();
  public $autocomplete = false;

  const inactivity_max_time = '24 hours';

  public function __construct($form_name = null) {
    if($this->form_id === null){
      $this->form_id = uniqid('magic_form_');
    }
    $this->set_form_name($form_name);
    $this->created = date("Y-m-d H:i:s");
    $this->uid = user_active_record::current()->uid;
  }

  public function __destruct() {
    // TODO: Work out why this crashes Apache. :| Hard.
    //$this->save(false);
  }

  public function __save(){
    return $this->save(true);
  }

  public function __pre_save(){
    $this->__magic_form_serialise();
  }

  public function __post_save(){
    $this->__magic_form_deserialise();
  }

  public function __post_construct(){
    $this->__magic_form_deserialise();
  }

  private function __magic_form_serialise() {
    if (is_array($this->form_elements)      || is_object($this->form_elements))       $this->form_elements      = $this->__encode($this->form_elements);
    if (is_array($this->submit_function)    || is_object($this->submit_function))     $this->submit_function    = $this->__encode($this->submit_function);
    if (is_array($this->submit_destination) || is_object($this->submit_destination))  $this->submit_destination = $this->__encode($this->submit_destination);
    if (is_array($this->classes)            || is_object($this->classes))             $this->classes            = $this->__encode($this->classes);
    if (is_array($this->fields_to_omit)     || is_object($this->fields_to_omit))      $this->fields_to_omit     = $this->__encode($this->fields_to_omit);
    if (is_array($this->autocomplete)       || is_object($this->autocomplete))        $this->autocomplete       = $this->__encode($this->autocomplete);
  }
  private function __magic_form_deserialise(){
    if(is_string($this->form_elements))       $this->form_elements      = $this->__decode($this->form_elements);
    if(is_string($this->submit_function))     $this->submit_function    = $this->__decode($this->submit_function);
    if(is_string($this->submit_destination))  $this->submit_destination = $this->__decode($this->submit_destination);
    if(is_string($this->classes))             $this->classes            = $this->__decode($this->classes);
    if(is_string($this->fields_to_omit))      $this->fields_to_omit     = $this->__decode($this->fields_to_omit);
    if(is_string($this->autocomplete))        $this->autocomplete       = $this->__decode($this->autocomplete);
  }

  public function __encode($thing){
    $serialised = serialize($thing);
    $encoded = base64_encode($serialised);
    return $encoded;
  }

  public function __decode($encoded){
    $serialized = base64_decode($encoded);
    $thing = unserialize($serialized);
    return $thing;
  }

  public function set_form_name($name){
    $name = str_replace(" ", "-", $name);
    $name = str_replace("_", "-", $name);
    $this->form_name = $name;
    return $this;
  }

  public function get_form_name(){
    return $this->form_name;
  }

  public function set_autocomplete_enable(){
    return $this->set_autocomplete(true);
  }
  public function set_autocomplete_disable(){
    return $this->set_autocomplete(false);
  }
  public function set_autocomplete($mode){
    $this->autocomplete = $mode;
    return $this;
  }
  public function get_autocomplete(){
    return $this->autocomplete;
  }

  public function set_render_mode($render_mode){
    $this->render_mode = $render_mode;
    return $this;
  }

  public function get_render_mode(){
    return $this->render_mode;
  }

  static public function cleanup_expired_forms() {
    // Expire old magic forms
    $expired_forms = magic_form::search()->where('created', date('Y-m-d H:i:s', strtotime(self::inactivity_max_time . ' ago')), '<=')->exec();
    foreach($expired_forms as $expired_form){
      /* @var $expired_form magic_form */
      $expired_form->delete();
    }
  }

  public function add_field(magic_form_item $field) {
    $this->form_elements[$field->get_name()] = $field;
    $this->__save();
    return $this;
  }

  public function add_fields(){
    foreach(func_get_args() as $argument){
      $argument->set_scope($this);
      $this->add_field($argument);
    }
    return $this;
  }

  public function omit_field($name){
    $this->fields_to_omit[] = $name;
    return $this;
  }

  public function omit_fields(){
    foreach(func_get_args() as $name){
      $this->omit_field($name);
    }
    return $this;
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

    $all_elements = array();
    $all_elements = array_merge($all_elements, $this->form_elements);
    $output_elements = array();

    $output_elements = array_merge($output_elements, $all_elements);

    foreach($all_elements as &$element){
      if($element instanceof magic_form_group){
        foreach($element->get_fields() as $field){
          $output_elements[] = $field;
        }
      }
    }

    return $output_elements;
  }

  public function __toString() {
    $view = new StdClass();
    $view->form_rows = $this->form_elements;
    if(count($view->form_rows) > 0){
      foreach($view->form_rows as &$row){
        /* @var $row magic_form_item */
        $row->set_scope($this);
        if(in_array($row->get_name(), $this->fields_to_omit)){
           unlink($row);
        }
      }
      $view->action = $this->get_action();
      $view->form_name = $this->get_form_name();
      $view->form_id = $this->get_form_id();
      $view->classes = $this->get_classes();
      $view->autocomplete = $this->autocomplete;
      $view->scope = $this;
      $this->__save();
      return magic_forms_template_view($this->get_render_mode() . "/" . "form.phtml", $view);
    }else{
      return "No form elements";
    }
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

  public function set_submit_destination($submit_destination){
    $this->submit_destination = $submit_destination;
    return $this;
  }

  public function get_submit_destination(){
    return $this->submit_destination;
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

          if (!$item instanceof magic_form_field) {
            $item = new magic_form_field();
            $item->set_name($key);
            $item->set_label($key);
          }
          $item->set_value($value);
          $this->form_elements[$key] = $item;
      }
    }
  }

  public function get_form_id() {
    return $this->form_id;
  }

  public static function process($magic_form_id) {
    $magic_form = magic_form::search()->where('form_id', $magic_form_id)->execOne();
    if ($magic_form instanceof magic_form) {
      $magic_form->do_submit();
    } else {
      drupal_set_message("Uhoh... The form expired after " . self::inactivity_max_time . "! Please try again.", "error");
      header("Location: {$_SERVER['HTTP_REFERER']}");
      exit;
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
    $classes = array();
    if($this->get_form_name()){
      $classes[] = magic_forms_mangle_to_css_class($this->get_form_name());
    }
    $classes = array_merge($classes, $this->classes);
    return $classes;
  }
}