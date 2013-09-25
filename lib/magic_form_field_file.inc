<?php

class magic_form_field_file extends magic_form_field
{
    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return magic_forms_template_view("form.file.phtml", $view);
    }

    public function get_data(){
        krumo($_FILES);
        krumo($this->get_name());
        krumo($this->get_label());
        $tmp_name = $_FILES[$this->get_name()]['tmp_name'];
        echo "Loading {$tmp_name}\n";
        return file_get_contents($tmp_name);
    }
}