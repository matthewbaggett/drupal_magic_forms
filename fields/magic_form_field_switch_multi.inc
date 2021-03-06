<?php

class magic_form_field_switch_multi extends magic_form_field_multi
{
    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return $this->render("form.switch_multi.phtml", $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates_bootstrap');
    }

    public function get_value()
    {
        if (parent::get_value() === null) {
            return array();
        } else {
            return parent::get_value();
        }
    }
}
