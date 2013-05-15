<?php

class magic_form_field_multi extends magic_form_field {
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
}