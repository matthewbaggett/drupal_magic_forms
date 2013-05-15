<?php

class magic_form_group extends magic_form_item {
  private $fields;
  private $group_name;

  public function __construct($group_name = null) {
    $this->group_name = $group_name;
  }

  public function add_field(magic_form_field $field) {
    $this->fields[] = $field;
    return $this;
  }

  public function get_fields() {
    return $this->fields;
  }

  public function get_group_name() {
    return t($this->group_name);
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return magic_forms_template_view("form.group.phtml", $view);
  }
}