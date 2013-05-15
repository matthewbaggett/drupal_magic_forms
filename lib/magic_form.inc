<?php
class magic_form {
  private $form_elements;

  public function add_field(magic_form_item $field) {
    $this->form_elements[] = $field;
    return $this;
  }

  public function __toString() {
    $view = new StdClass();
    $view->form_rows = $this->form_elements;
    $view->action = $this->get_action();
    return magic_forms_template_view("form.phtml", $view);
  }

  public function get_action(){
    return $_SERVER['REQUEST_URI'];
  }
}