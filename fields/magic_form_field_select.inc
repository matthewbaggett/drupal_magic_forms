<?php

class magic_form_field_select extends magic_form_field_multi {
  protected $allow_null_value = false;

  /**
   * @param null $name Name
   * @param null $label Label
   * @param null $value Default Value
   * @return magic_form_field_select
   */
  public static function factory($name = null, $label = null, $value = null) {
    return parent::factory($name,$label,$value);
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.select.phtml", $view, $this->get_scope()->get_templates_directory());
  }

  public function allow_null_value() {
    $this->allow_null_value = true;
    return $this;
  }

  public function ban_null_value() {
    $this->allow_null_value = false;
    return $this;
  }

  public function null_value_allowed() {
    return $this->allow_null_value ? true : false;
  }
}