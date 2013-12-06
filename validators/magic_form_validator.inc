<?php

class magic_form_validator {
  protected $passed_params;
  protected $form_field;

  public function __construct($var1 = null, $var2 = null, $var3 = null) {
    $this->passed_params = array($var1, $var2, $var3);
  }

  public function set_form_field(magic_form_field $form_field) {
    $this->form_field = $form_field;
    return $this;
  }

  public function get_param($i) {
    return $this->passed_params[$i];
  }

  public function test($data) {
    $class = get_called_class();
    throw new Exception("{$class} needs to implement test()!");
  }

  protected function sanitise($data) {
    $data = trim($data);
    return $data;
  }

  public function __toJsonArray() {
    $array = array();
    $array['type'] = str_replace('magic_form_validator_', '', get_called_class());
    foreach (get_object_vars($this) as $variable => $value) {
      $array[$variable] = $value;
    }
    return $array;
  }
}

