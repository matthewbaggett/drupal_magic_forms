<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class HiddenInputTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_hidden_field';
        $this->input_default_label = 'Test hidden field';
    }

    public function testHiddenInput()
    {
        //Create Text Input
        $new_field = magic_form_field_hidden::factory($this->input_default_name, $this->input_default_label, 'testhiddenvalue');
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_hidden_field = $form->find("input[name=test_hidden_field]")[0];
        //Check Text Field
        $this->assertEquals("hidden", $test_hidden_field->attr['type'], "Type Equals Hidden");
        $this->assertEquals($this->input_default_name, $test_hidden_field->attr['name'], "Name Equals test_text_field");
        $this->assertEquals("testhiddenvalue", $test_hidden_field->attr['value'], "Value Equals testhiddenvalue");


    }
}
