<?php

class magic_form_field_file extends magic_form_field {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.file.phtml", $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates_bootstrap');
  }

  public function get_data() {
    $tmp_name = $_FILES[$this->get_name()]['tmp_name'];
    return file_get_contents($tmp_name);
  }

  public function has_file() {
    if ($_FILES[$this->get_name()]['tmp_name'] != false) {
      return true;
    }
    return false;
  }
}