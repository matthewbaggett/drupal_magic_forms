<?php

class magic_form_field_date extends magic_form_field_text {

  protected $_support_date = true;
  protected $_support_time = true;

  /**
   * @param null $name Internal Name for this field
   * @param null $label Visible Name for this field
   * @param null $value Default or Initial Value
   *
   * @return magic_form_field_date
   */
  public static function factory($name = null, $label = null, $value = null) {
    return parent::factory($name, $label, $value);
  }

  /**
   * Sanitise the date given
   * @return string
   */
  public function get_value() {
    return date(
      $this->get_format(),
      strtotime(parent::get_value())
    );
  }

  /**
   * get the format for date() that this object should use.
   * @return string
   */
  private function get_format() {
    $format_sections = array();
    if ($this->get_support_date()) {
      $format_sections[] = 'Y-m-d';
    }
    if ($this->get_support_time()) {
      $format_sections[] = 'H:i:s';
    }
    return implode(" ", $format_sections);
  }

  /**
   * Set weather or not magic_form_field_date should support dates
   *
   * @param $state bool true or false
   *
   * @return magic_form_field_date $this
   */
  public function set_support_date($state) {
    $this->_support_date = $state;
    return $this;
  }

  /**
   * Get weather or not magic_form_field_date should support dates
   *
   * @return bool
   */
  public function get_support_date() {
    return $this->_support_date;
  }

  /**
   * Set weather or not magic_form_field_date should support times
   *
   * @param $state bool true or false
   *
   * @return magic_form_field_date $this
   */
  public function set_support_time($state) {
    $this->_support_time = $state;
    return $this;
  }

  /**
   * Get weather or not magic_form_field_date should support times
   *
   * @return bool
   */
  public function get_support_time() {
    return $this->_support_time;
  }


}