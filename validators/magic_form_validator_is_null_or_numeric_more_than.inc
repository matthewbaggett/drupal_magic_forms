<?php

class magic_form_validator_is_null_or_numeric_more_than extends magic_form_validator_is_numeric_more_than implements magic_form_validator_interface
{

    public function test($data)
    {

      //null ok
        if (trim($data) == null) {
            return true;
        };

      //test numeric
        return parent::test($data);
    }
}
