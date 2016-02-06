<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class SpineditInputTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_spinedit_field';
        $this->input_default_label = 'Test spinedit field';
    }

    public function testSpineditInput()
    {

        // Add SpinEdit field
        $quantity = magic_form_field_spinedit::factory($this->input_default_name, $this->input_default_label);
        $quantity->set_min(5)
            ->set_max(10)
            ->set_step(1);
        $this->magic_form->add_field($quantity);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_spinedit_field = $form->find("input[name=".$this->input_default_name."]")[0];

        //Check Spinedit Field
        $this->assertEquals("text", $test_spinedit_field->attr['type'], "Type Equals Text");
        $this->assertEquals($this->input_default_name, $test_spinedit_field->attr['name'], "Name Equals ".$this->input_default_name);

    }
}
