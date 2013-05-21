<?php

class magic_form_field_multi extends magic_form_field {
  protected $options;

  /**
   * @param      $value The label of the option selected
   * @param null $key The value of the option selected - Unique.
   */
  public function add_option($value, $key = null) {
    if ($key) {
      $this->options[$key] = $value;
    } else {
      $this->options[] = $value;
    }
  }

  /**
   * Get assigned options#
   *
   * @return array of options
   */
  public function get_options() {
    return $this->options;
  }

  /**
   * Pass an array of options to the magic form field in the format key => value
   *
   * @param $array_of_options
   *
   * @return $this
   */
  public function add_options($array_of_options){
    foreach($array_of_options as $key => $value){
      $this->add_option($key, $value);
    }
    return $this;
  }
}