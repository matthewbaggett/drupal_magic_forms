<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class RadioInputTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_radio_field';
        $this->input_default_label = 'Test radio field';
    }

    public function testRadioInput()
    {
        // Create a Salutation
        $new_field = magic_form_field_radio::factory($this->input_default_name, $this->input_default_label);
        // Add some options to it.
        $new_field->add_options(array(
            1 => 'Test Value 1',
            2 => 'Test Value 2'
        ));
        // Add them to the form
        $this->magic_form->add_fields($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Radio Inputs
        $test_radio_field1 = $form->find("input[id=".$this->input_default_name."-test-value-1]")[0];
        $test_radio_field2 = $form->find("input[id=".$this->input_default_name."-test-value-2]")[0];


        //Check Radio Inputs
        $this->assertEquals($this->input_default_name, $test_radio_field1->attr['name'], "Radio 1 Name Equals ".$this->input_default_name);
        $this->assertEquals($this->input_default_name, $test_radio_field2->attr['name'], "Radio 2 Name Equals ".$this->input_default_name);

        //Check Labels
        $test_radio_1_field_label = $form->find("label[for=".$this->input_default_name."-test-value-1]")[0];
        $this->assertEquals($this->input_default_name."-test-value-1", $test_radio_1_field_label->attr['for'], "Check Label Radio 1");
        $this->assertEquals("Test Value 1", $test_radio_1_field_label->innertext(), "Check Label Text Radio 1");

        $test_radio_2_field_label = $form->find("label[for=".$this->input_default_name."-test-value-2]")[0];
        $this->assertEquals($this->input_default_name."-test-value-2", $test_radio_2_field_label->attr['for'], "Check Label Radio 2");
        $this->assertEquals("Test Value 2", $test_radio_2_field_label->innertext(), "Check Label Text Radio 2");
    }
}
