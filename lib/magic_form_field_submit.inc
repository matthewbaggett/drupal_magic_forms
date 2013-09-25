<?php

class magic_form_field_submit extends magic_form_field_button{
    public function __toString(){
        $view = new StdClass();
        $view->field = $this;
        return magic_forms_template_view("form.submit.phtml", $view);
    }

    public function get_data(){
        krumo($_FILES);
        krumo($this->get_name());
        $tmp_name = $_FILES[$this->get_name()]['tmp_name'];
        echo "Loading {$tmp_name}\n";
        return file_get_contents($tmp_name);
    }
}