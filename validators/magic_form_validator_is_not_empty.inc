<?php
class magic_form_validator_is_not_empty extends magic_form_validator implements magic_form_validator_interface
{
    public function test($data)
    {


        if (strlen(trim($data)) > 0) {
            return true;
        }
        return false;
    }

    public function user_friendly_failure_message($message_params)
    {
        return t("Field must not be empty");
    }
}
