<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class RangeInputTest extends PHPUnit_Framework_TestCase {

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp(){
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_range_field';
        $this->input_default_label = 'Test range field';
    }

    public function testRangeInput()
    {
        //Create Text Input
        $new_field = magic_form_field_range::factory($this->input_default_name, $this->input_default_label);

        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();


        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_range_field = $form->find("input[data-slider=true]")[0];


        //Check Text Field
        $this->assertEquals("text", $test_range_field->attr['type'], "Type Equals Text");
        $this->assertContains($this->input_default_name, $test_range_field->attr['id'], "ID is like ".$this->input_default_name);

        //Check set_label
        $test_test_field_label = $form->find("label[for=".$this->input_default_name."]")[0];
        $this->assertEquals($this->input_default_name, $test_test_field_label->attr['for'], "Check Label");
        $this->assertEquals($this->input_default_label, $test_test_field_label->innertext(), "Check Label Text");

    }

    public function testRangeInputOptions()
    {
        //Create Text Input
        $new_field = magic_form_field_range::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_min(2)
            ->set_max(256)
            ->set_step(1)
            ->set_unit('GB')
            ->set_options(array('show_tooltip' => true,'show_increments' => false,'show_minmax' => true));

        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();


        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_range_field = $form->find("input[data-slider=true]")[0];

        //Check Range
        $this->assertContains("2,256", $test_range_field->attr['data-slider-range'], "Range");
        //Check Step
        $this->assertContains("1", $test_range_field->attr['data-slider-step'], "Step");
        //Check Unit
        $this->assertContains("GB", $test_range_field->attr['data-slider-unit'], "Unit");
        //Check Tooltip
        $this->assertContains("true", $test_range_field->attr['data-slider-tooltip'], "Tooltip");

    }


    public function testRangeInputIncrements()
    {
        //Create Text Input
        $new_field = magic_form_field_range::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_increments(array(1,2,3,4))
            ->set_options(array('show_tooltip' => true,'show_increments' => false,'show_minmax' => true));

        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_range_field = $form->find("input[data-slider=true]")[0];

        //Check Range
        $this->assertContains("1,2,3,4", $test_range_field->attr['data-slider-values'], "Range");

    }
}

