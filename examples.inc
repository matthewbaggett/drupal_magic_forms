<?php

function magic_form_examples()
{
    drupal_set_title("Magic Form Examples");
  // Create a new form
    $form = magic_form::factory('my-form');

    $form->set_templates_directory('templates_bootstrap');

    $personal_details = magic_form_group::factory('Personal Details');

  // Create a name field
    $name = magic_form_field_text::factory('name', 'Name');
  // Set a default
    $name->set_default_value("Joe Blogs");
  // Set av value
    $name->set_value("Mary Sue");

  // Create a Salutation
    $salutation = magic_form_field_select::factory('salutation', 'Salutation');
  // Add some options to it.
    $salutation->add_options(array(
    0 => 'Please Select',
    1 => 'Mr',
    2 => 'Mrs',
    3 => 'Miss',
    4 => 'Dr'
    ));
  // Add a validator. More than 0 prevents someone using "Please Select"
    $salutation->add_validator(new magic_form_validator_is_numeric_more_than(0));

  // Add them to the form
    $personal_details->add_fields($name, $salutation);

  // Add the personal details group to the form
    $form->add_field($personal_details);

  // Add things retroactively to the personal details group.
    $personal_details
    ->add_field(
        magic_form_field_text::factory('phone-number', 'Phone Number')
        ->make_mandatory()
        ->set_default_value('07541 059 344')
        ->add_validator(new magic_form_validator_is_valid_phonenumber())
    )->add_field(
        magic_form_field_text::factory('email', 'Email')
        ->make_mandatory()
        ->set_default_value('matthew@fouroneone.us')
        ->add_validator(new magic_form_validator_is_email())
    );






  //Put email above phone number
    $name_weight = $form->get_field('name')->get_weight();
    $salutation_weight = $form->get_field('salutation')->get_weight();
    $form->get_field('name')->set_weight($salutation_weight);
    $form->get_field('salutation')->set_weight($name_weight);

  // Add items direct to the form
    $form->add_field(
        magic_form_field_textarea::factory('ramble', 'Comment', 'Must be > 50 char, < 100 char')
        ->add_validators(
            new magic_form_validator_is_length_less_than(100),
            new magic_form_validator_is_length_more_than(50)
        )
    )->add_fields(
        magic_form_field_text::factory('phone', 'Phone', '0800 000000')
        ->add_validator(new magic_form_validator_is_valid_phonenumber()),
        magic_form_field_text::factory('email', 'Email', 'joe@example.com')
        ->add_validator(new magic_form_validator_is_email())
    )
    ->add_field(magic_form_field_date::factory('date_time', 'Date & Time')->set_support_date(true)->set_support_time(true))
    ->add_field(magic_form_field_date::factory('date', 'Date Only')->set_support_date(true)->set_support_time(false))
    ->add_field(magic_form_field_date::factory('time', 'Time Only')->set_support_date(false)->set_support_time(true));

    magic_form_field_date::factory('date_time', 'Date & Time')->set_default_value(date("Y-m-d H:i:s"));

    $checkbox = new magic_form_field_checkbox('checkbox', 'I like checkboxes');

    $form->add_field($checkbox);
  // Add a Series of checkboxes for non-mutually-exclusive options.
    $options = new magic_form_field_checkbox_multi('room-options', 'Room Options');
    $options->add_options(array(
    'aircon' => 'Air Conditioning',
    'nosmoke' => 'Non Smoking',
    'seaview' => 'Sea View',
    'annoying' => 'No Annoying Neighbours',
    'disabled' => 'Disabled access',
    'ground' => 'Ground floor',
    'top' => 'Top floor',
    ));
    $options->set_value(array("disabled", "top"));
    $form->add_field($options);


  // Add Range field

    $distance = magic_form_field_range::factory('distance', 'Distance');
    $distance->set_min(20)
    ->set_max(30)
    ->set_step(5)
    ->set_unit('GB')
    ->set_options(array('show_tooltip' => true,'show_increments' => false,'show_minmax' => true));
    $form->add_field($distance);



    /*drupal_add_js('jQuery(function() {
         jQuery( ".field-distance .range_group .slider" ).mouseup(function() {
            console.log("mouse up");
    });

    });','inline');*/

    $distance2 = magic_form_field_range::factory('distance2', 'Distance Disabled');
    $distance2->set_min(2)
    ->set_max(256)
    ->set_step(1)
    ->set_unit('GB')
    ->set_options(array('show_tooltip' => true,'show_increments' => false,'show_minmax' => true))
    ->disable();
    $form->add_field($distance2);


    $incredistance = magic_form_field_range::factory('distanceincrements', 'Distance Increments');
    $incredistance->set_increments(array(1,3,5,7,9,200))
                  ->set_unit('GB')
                  ->set_options(array('show_tooltip' => true, 'show_increments' => false,'show_minmax' => true));
    $form->add_field($incredistance);



  // Add Switch field
    $switch = new magic_form_field_switch('switch', 'Switch');
    $switch->set_attributes(array("partID"=>"12", "asdasdsad" => "34"));
    $form->add_field($switch);



    drupal_add_js('jQuery(function() {
       jQuery(".field-switch").on("switchChange","input", function(event, state) {
        console.log("CHANGE");
    });

   });', 'inline');


  // Add Switch field
    $switch = new magic_form_field_switch('switchdisabled', 'Switch Disabled');
    $switch->disable();
    $form->add_field($switch);






    $multiswitch = new magic_form_field_switch_multi('room-options2', 'Room Options 2');
    $multiswitch->add_options(array(
    'FW' => 'FW',
    'FWIPS' => 'FW+IPS',
    'NGFW' => 'NGFW',
    'NGTP' => 'NGTP'
    ));
    $multiswitch->set_value("NGFW");
    $multiswitch->set_value("NGFW");
    $form->add_field($multiswitch);



    $multiswitch = new magic_form_field_switch_multi('room-options2disabled', 'Room Options 2 Disabled');
    $multiswitch->add_options(array(
    'FW' => 'FW',
    'FWIPS' => 'FW+IPS',
    'NGFW' => 'NGFW',
    'NGTP' => 'NGTP'
    ));
    $multiswitch->set_value("NGFW");
    $multiswitch->set_value("NGFW");
    $multiswitch->disable();
    $form->add_field($multiswitch);





  // Add SpinEdit field
    $quantity = magic_form_field_spinedit::factory('quantity', 'Quantity');
    $quantity->set_min(5)
          ->set_max(10)
          ->set_step(1)
          ->set_attributes(array("partID"=>"12", "asdasdsad" => "34"));
    $form->add_field($quantity);



  // Add Submit button to form
    $form->add_field(magic_form_field_submit::factory('submit', 'Submit'));

  // This is our submit handler.
    $form->submit(function (magic_form $form) {
        require_once(drupal_get_path("module", "devel") . "/krumo/class.krumo.php");
        krumo($form->get_fields());
        drupal_set_message("Submit happened in form {$form->magic_form_id} / {$form->form_id}");
    });

  // Check to see if an earlier, updated build of this form exists.
    magic_form::check_for_updated_form($form);

  // render the form.
    return $form->__toString();
}
