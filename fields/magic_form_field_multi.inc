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
    return $this;
  }

  /**
   * Get assigned options
   *
   * @return array of options
   */
  public function get_options() {
    return $this->options;
  }

  /**
   * Set assigned options
   * @param array $options options
   * @return $this
   */
  public function set_options($options) {
    $this->options = $options;
    return $this;
  }

  /**
   * Pass an array of options to the magic form field in the format key => value
   *
   * @param $array_of_options
   *
   * @return magic_form_field_multi
   */
  public function add_options($array_of_options) {
    foreach ($array_of_options as $key => $value) {
      if (class_exists('active_record')) {
        if ($value instanceof active_record) {
          $this->add_option($value->get_label(), $value->get_id());
          continue;
        }
      }
      $this->add_option($value, $key);
    }
    return $this;
  }

  /**
   * Remove an option by key
   *
   * @param $key_of_option
   *
   * @return magic_form_field_multi
   */
  public function remove_option($key_of_option) {
    unset($this->options[$key_of_option]);
    return $this;
  }

  /**
   * Remove an array of options by key
   *
   * @param $array_of_keys
   *
   * @return magic_form_field_multi
   */
  public function remove_options($array_of_keys) {
    foreach ($array_of_keys as $key) {
      $this->remove_option($key);
    }
    return $this;
  }
}