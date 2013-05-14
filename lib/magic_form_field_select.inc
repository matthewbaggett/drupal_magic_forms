<?php

class magic_form_field_select extends magic_form_field {
  protected $options;

  public function add_option($value, $key = null) {
    if ($key) {
      $this->options[$key] = $value;
    } else {
      $this->options[] = $value;
    }
  }

  public function get_options() {
    return $this->options;
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return magic_forms_template_view("form.select.phtml", $view);
  }
}