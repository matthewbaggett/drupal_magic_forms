<?php

class magic_form_group extends magic_form_item {
  private $fields;

  public function add_field(magic_form_field $field) {
    $this->fields[] = $field;
    return $this;
  }

  public function get_fields() {
    return $this->fields;
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return magic_forms_template_view("form.group.phtml", $view);
  }
}