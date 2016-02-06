<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class SelectInputTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_select_field';
        $this->input_default_label = 'Test select field';
    }

    public function testSelectInput()
    {
        $new_field = magic_form_field_select::factory($this->input_default_name, $this->input_default_label);
        // Add some options to it.
        $new_field->add_options(array(
            0 => 'Please Select',
            1 => 'Test Value 1',
            2 => 'Test Value 2'
        ));
        // Add them to the form
        $this->magic_form->add_fields($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Select Input
        $test_select_field = $form->find("select[name=".$this->input_default_name."]")[0];

        //Check Select Field
        $this->assertEquals($this->input_default_name, $test_select_field->attr['name'], "Name Equals ".$this->input_default_name);

        //Check Label
        $test_select_field_label = $form->find("label[for=".$this->input_default_name."]")[0];
        $this->assertEquals($this->input_default_name, $test_select_field_label->attr['for'], "Check Label");
        $this->assertEquals($this->input_default_label, $test_select_field_label->innertext(), "Check Label Text");
    }

    function testSelectInputAllowNull()
    {
        $new_field = magic_form_field_select::factory($this->input_default_name, $this->input_default_label);
        // Add some options to it.
        $new_field->add_options(array(
            0 => 'Please Select',
            1 => 'Test Value 1',
            2 => 'Test Value 2'
        ))->allow_null_value();

        // Add them to the form
        $this->magic_form->add_fields($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Select Input
        $test_select_field = $form->find("select[name=".$this->input_default_name."]")[0];
    }

    function testSelectInputBanNull()
    {
        $new_field = magic_form_field_select::factory($this->input_default_name, $this->input_default_label);
        // Add some options to it.
        $new_field->add_options(array(
            0 => 'Please Select',
            1 => 'Test Value 1',
            2 => 'Test Value 2'
        ))->ban_null_value();

        // Add them to the form
        $this->magic_form->add_fields($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Select Input
        $test_select_field = $form->find("select[name=".$this->input_default_name."]")[0];
    }
}
