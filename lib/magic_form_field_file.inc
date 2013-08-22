<?php

class magic_form_field_file extends magic_form_field
{
    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return magic_forms_template_view("form.file.phtml", $view);
    }
}