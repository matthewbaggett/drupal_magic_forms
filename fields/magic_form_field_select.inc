<?php

class magic_form_field_select extends magic_form_field_multi {
  protected $allow_null_value = false;

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.select.phtml", $view);
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