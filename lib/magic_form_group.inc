<?php

class magic_form_group extends magic_form_item
{
    private $fields;
    private $group_name;

    public function __construct($group_name = null)
    {
        $this->group_name = $group_name;
    }

    public function add_field(magic_form_item $field)
    {
        $this->fields[$field->get_name()] = $field;
        return $this;
    }

    public function get_fields()
    {
        return $this->fields;
    }

    public function get_group_name()
    {
        return t($this->group_name);
    }

    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return magic_forms_template_view("form.group.phtml", $view);
    }

    public function get_name()
    {
        return $this->get_group_name();
    }

    static public function factory($group_name = null)
    {
        return new magic_form_group($group_name);
    }

    public function add_fields()
    {
        foreach (func_get_args() as $argument) {
            $this->add_field($argument);
        }
        return $this;
    }
}