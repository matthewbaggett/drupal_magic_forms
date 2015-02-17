<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class DataTableInputTest extends PHPUnit_Framework_TestCase {

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp(){
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_datatable_field';
        $this->input_default_label = 'Test datatable';
    }

    public function testDataTableInput()
    {
        //Create Text Input
        $new_field = magic_form_field_datatable::factory($this->input_default_name, $this->input_default_label);

        $new_field->add_rows(array(
            'TestColumn' => "Test Row",
            'TestColumn 2'   => "Test Row 2",
            'TestColumn 3' => l("Finish", "test/link/here")
        ));

        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("table[id=".$this->input_default_name."]")[0];

        //Check Text Field
        $this->assertEquals($this->input_default_name, $test_text_field->attr['id'], "Name Equals ".$this->input_default_name);

        //Check set_label
        $test_test_field_label = $form->find("label[for=".$this->input_default_name."]")[0];
        $this->assertEquals($this->input_default_name, $test_test_field_label->attr['for'], "Check Label");
        $this->assertEquals($this->input_default_label, $test_test_field_label->innertext(), "Check Label Text");
    }
}