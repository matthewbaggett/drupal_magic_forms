<?php

class magic_form_field_datatable extends magic_form_field {
  protected $rows;

  public static function factory($name = null, $label = null) {
    $class = get_called_class();
    $instance = new $class($name, $label);
    return $instance;
  }

  public function __construct($name = null, $label = null) {
    $this->name = $name;
    $this->label = t($label);
  }

  public function add_row($keyed_row) {
    $this->rows[] = $keyed_row;
  }

  public function get_rows() {
    return $this->rows;
  }

  public function get_headings(){
    return array_keys(end($this->rows));
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return magic_forms_template_view("form.datatable.phtml", $view);
  }
}