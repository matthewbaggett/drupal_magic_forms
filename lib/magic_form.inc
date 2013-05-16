<?php
class magic_form {
  private $form_id;

  private $form_elements;

  private $submit_function;

  const inactivity_max_time = '15 minutes';

  public function __construct() {
    $this->form_id = uniqid('magic_form_');

    // Expire old magic forms
    foreach ($_SESSION['magic_forms'] as $form_id => $form_container) {
      if (strtotime($form_container['created']) < strtotime(self::inactivity_max_time . " ago")) {
        unset($_SESSION['magic_forms'][$form_id]);
      }
    }
  }

  public function __destruct() {
    $_SESSION['magic_forms'][$this->form_id] = array( #
      'created' => date("Y-m-d H:i:s"),
      'form' => serialize($this),
    );
  }

  public function add_field(magic_form_item $field) {
    $this->form_elements[] = $field;
    return $this;
  }

  public function __toString() {
    $view = new StdClass();
    $view->form_rows = $this->form_elements;
    $view->action = $this->get_action();
    $view->form_id = $this->get_form_id();
    return magic_forms_template_view("form.phtml", $view);
  }

  public function get_action() {
    return $_SERVER['REQUEST_URI'];
  }

  public function submit($submit_function) {
    $this->submit_function = new magic_serialisable_closure($submit_function);
    return $this;
  }

  public function do_submit() {
    $this->submit_function->__invoke();
  }

  public function get_form_id() {
    return $this->form_id;
  }

  public static function process($magic_form_id) {
    if (!isset($_SESSION['magic_forms'][$magic_form_id])) {
      drupal_set_message("Uhoh... The form expired after " . self::inactivity_max_time . "! Please try again."); #
      header("Location: {$_SERVER['HTTP_REFERER']}");
    } else {
      $form = unserialize($_SESSION['magic_forms'][$magic_form_id]['form']);
      $form->do_submit();
    }
    die($magic_form_id);
  }
}