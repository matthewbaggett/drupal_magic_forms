<?php

class magic_form_field_datatable extends magic_form_field {
  protected $rows;
  private $columns;

  public static function factory($name = null, $label = null, $value = null) {
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
    return $this;
  }

  public function add_rows($array_of_rows) {
    foreach ($array_of_rows as $row) {
      $this->add_row($row);
    }
    return $this;
  }

  public function get_rows() {
    return $this->rows;
  }

  public function get_headings() {
    if(count($this->columns)){
      return $this->columns;
    }else{
      return array_keys(end($this->rows));
    }
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.datatable.phtml", $view);
  }

  public function define_columns($columns){
    $this->columns = $columns;
    return $this;
  }
}