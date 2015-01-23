<?php

class magic_form_field_submit extends magic_form_field_button {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.submit.phtml", $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates_bootstrap');
  }


}