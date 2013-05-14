<?php

class magic_form_field {
  protected $name = null;
  protected $label = null;
  protected $default_value = null;
  protected $value = null;
  protected $disabled = false;

  public static function factory($name = null, $label = null, $value = null) {
    $class = get_called_class();
    $instance = new $class($name, $label, $value);
    return $instance;
  }

  public function __construct($name = null, $label = null, $value = null) {
    $this->name = $name;
    $this->label = t($label);
    $this->value = $value;
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return magic_forms_template_view("form.input.phtml", $view);
  }

  public function get_name() {
    return $this->name;
  }

  public function set_name($name) {
    $this->name = $name;
    return $this;
  }

  public function get_label() {
    return $this->label;
  }

  public function set_label($label) {
    $this->label = $label;
    return $this;
  }

  public function get_default_valu() {
    return $this->default_valu;
  }

  public function set_default_value($default_valu) {
    $this->default_valu = $default_valu;
    return $this;
  }

  public function get_value() {
    return $this->value;
  }

  public function set_value($value) {
    $this->value = $value;
    return $this;
  }

  public function disable() {
    $this->disabled = true;
    return $this;
  }

  public function enable() {
    $this->disabled = false;
    return $this;
  }

  public function is_disabled() {
    return $this->disabled;
  }
}