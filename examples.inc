<?php

function magic_form_examples(){
  $form = magic_form::factory('my-form')
    ->add_field(
      magic_form_field_text::factory('phone-number', 'Phone Number')
        ->is_mandatory()
        ->set_default_value('07541 059 344')
        ->add_validator(new magic_form_validator_is_valid_phonenumber())
    )->add_field(
      magic_form_field_text::factory('email','Email')
        ->is_mandatory()
        ->set_default_value('matthew@fouroneone.us')
        ->add_validator(new magic_form_validator_is_email())
    )->add_field(
      magic_form_field_textarea::factory('ramble','Comment','Must be > 50 char, < 100 char')
        ->add_validators(
          new magic_form_validator_is_less_than(100),
          new magic_form_validator_is_greater_than(50)
        )
    )/*->add_fields(
      magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
        ->add_validator(new magic_form_validator_is_valid_phonenumber())
        ->add_validator(new magic_form_validator_is_valid_email()),
      magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
        ->add_validator(new magic_form_validator_is_valid_phonenumber())
        ->add_validator(new magic_form_validator_is_valid_email()),
      magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
        ->add_validator(new magic_form_validator_is_valid_phonenumber())
        ->add_validator(new magic_form_validator_is_valid_email()),
      magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
        ->add_validator(new magic_form_validator_is_valid_phonenumber())
        ->add_validator(new magic_form_validator_is_valid_email())
    )*/;

  return $form->__toString();
}