<?php

class magic_form_group extends magic_form_item {
  public $fields;
  public $group_name;
  public $group_label;
  protected $classes = array();

  public function __construct($group_name = null, $group_label = null) {
    $this->set_group_name($group_name);
    $this->set_group_label($group_label);

    // Support legacy behaviour
    if ($group_label === null && $group_name !== null) {
    $this->set_group_label($group_name);
    }
  }

  /**
   * Add field to this group
   *
   * @param magic_form_item $field
   *
   * @return $this
   */
  public function add_field(magic_form_item $field) {
    $field->set_scope($this->get_scope());

    // Find heaviest item.
    $heaviest = null;
    if(count($this->fields) > 0){
      foreach($this->fields as $other_field){
        /* @var $other_field magic_form_item */
        $heaviest = $other_field->get_weight()> $heaviest || $heaviest === null ? $other_field->get_weight() : $heaviest;
      }
    }

    $field->set_weight($heaviest + 1);

    $this->fields[$field->get_weight() . "-" . $field->get_name()] = $field;
    return $this;
  }

  /**
   * Get fields attached to this group
   * @return mixed
   */
  public function get_fields() {
    if(count($this->fields) > 0){
      usort($this->fields, array($this, '_weight_sort'));
    }
    return $this->fields;
  }

  public function seek_field($name){
    foreach($this->fields as $element){
      if($element->get_name() == $name){
        return $element;
      }
      if($element instanceof magic_form_group){
        $found = $element->seek_field($name);
        if($found instanceof magic_form_item){
          return $found;
        }
      }
    }
    return false;
  }

  /**
   * Remove named field
   *
   * @param $field_name
   *
   * @return $this
   */
  public function remove_field($field_name){
    foreach($this->fields as $k => $form_element){
      if($form_element instanceof magic_form_field){
        if($form_element->get_name() == $field_name){
          unset($this->fields[$k]);
        }
      }
      if($form_element instanceof magic_form_group){
        $form_element->remove_field($field_name);
      }
    }
    return $this;
  }

  /**
   * Remove named fields
   *
   * @return $this
   */
  public function remove_fields(){
    foreach(func_get_args() as $argument){
      $this->remove_field($argument);
    }
    return $this;
  }

  private function _weight_sort( magic_form_item $a, magic_form_item $b ) {
    return $a->get_weight() == $b->get_weight() ? 0 : ( $a->get_weight() > $b->get_weight() ) ? 1 : -1;
  }

  /**
   * Set this groups name
   *
   * @param $group_name
   *
   * @return $this
   */
  public function set_group_name($group_name) {
    $this->group_name = $group_name;
    $this->add_class(magic_forms_mangle_to_css_class($group_name));
    return $this;
  }

  /**
   * Get this groups name
   *
   * @return mixed
   */
  public function get_group_name() {
    return $this->group_name;
  }

  public function set_group_label($group_label) {
    $this->group_label = $group_label;
    return $this;
  }

  public function get_group_label() {
    return t($this->group_label);
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.group.phtml", $view);
  }

  public function get_name() {
    return $this->get_group_name();
  }

  static public function factory($group_name = null) {
    return new magic_form_group($group_name);
  }

  public function add_fields() {
    foreach (func_get_args() as $argument) {
      $this->add_field($argument);
    }
    return $this;
  }

  public function add_class($class) {
    $this->classes[] = $class;
    return $this;
  }

  public function __toJsonArray() {
    $array = parent::__toJsonArray();
    $array['name'] = $this->get_group_name();
    return $array;
  }
}