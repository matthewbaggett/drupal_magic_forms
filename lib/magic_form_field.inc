<?php
class magic_form_field extends magic_form_item {
  protected $name = null;
  protected $label = null;
  protected $default_value = null;
  protected $value = null;
  protected $disabled = false;
  protected $errors = array();
  protected $classes = array();

  /**
   * @param null $name Internal Name for this field
   * @param null $label Visible Name for this field
   * @param null $value Default or Initial Value
   *
   * @return magic_form_field
   */
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
    return $this->render("form.input.phtml", $view);
  }

  /**
   * Get the name of this widget
   *
   * @return string
   */
  public function get_name() {
    return $this->name;
  }

  /**
   * Set the name for this widget
   *
   * @param $name
   *
   * @return $this
   */
  public function set_name($name) {
    $this->name = $name;
    return $this;
  }

  /**
   * Get the label of this widget
   *
   * @return string
   */
  public function get_label() {
    return $this->label;
  }

  /**
   * Set the label for this widget
   *
   * @param $label Label for this widget
   *
   * @return magic_form_field
   */
  public function set_label($label) {
    $this->label = $label;
    return $this;
  }

  /**
   * Get the default value of this widget
   *
   * @return string
   */
  public function get_default_value() {
    return $this->default_value;
  }

  /**
   * Set the default value of this widget
   *
   * @param $default_value
   *
   * @return magic_form_field
   */
  public function set_default_value($default_value) {
    $this->default_value = $default_value;
    return $this;
  }

  public function get_value() {
    return $this->value;
  }

  /**
   * @param $value
   *
   * @return magic_form_field
   */
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

  public function add_error($error) {
    $this->errors[] = $error;
    return $this;
  }

  public function has_errors() {
    return count($this->errors) > 0 ? true : false;
  }

  public function add_class($class) {
    $this->classes[] = $class;
    return $this;
  }

  public function get_classes() {
    if ($this->has_errors()) {
      $this->add_class("error");
    }
    if ($this->is_disabled()){
      $this->add_class('disabled');
    }else{
      $this->add_class('enabled');
    }
    return implode(" ", $this->classes);
  }
}