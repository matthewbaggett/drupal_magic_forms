jQuery(document).ready(function () {
  var form = jQuery('form.magic_form');
  jQuery('select, input, textarea', form).bind('change', function () {
    jQuery(this).addClass('changed');
  });
});

function magic_form_field(type, name, label, value) {
  if(typeof(value) == 'undefined'){
    value = '';
  }
  this.type = type;
  this.name = name;
  this.label = label;
  this.value = value;
  this.options = [];
  this.disabled = false;
  this.events = [];

  this._get_mass_selector = function(){
    return '' +
      '.form_row.field-' + this.name + ' input,' +
      '.form_row.field-' + this.name + ' textarea,' +
      '.form_row.field-' + this.name + ' select,' +
      '.form_row.field-' + this.name + '.form_radio .radio_group input[type=radio]'
  };

  this._get_input_field = function(){
    var selector = this._get_mass_selector();
    //console.log(selector, "Selector for " + this.name);
    return jQuery(selector);
  };

  this.set_value = function (value){
    if(typeof(value) !== 'undefined'){
      value = value.toString();
    }
    this.value = value;

    // Set the value
    this._get_input_field().val(value);
    this._get_input_field().attr('placeholder', value);

    // If its an option, we got a little more heavy liftin' to do.
    var select = jQuery('.form_row.field-' + this.name + ' select');
    if(select.length > 0){
      jQuery('option', select).removeAttr('selected');
      jQuery('option[value=' + value + ']', select).attr('selected', 'selected');
    }

    // Trigger changed state.
    this._get_input_field().trigger('change');
    return this;
  };

  this.get_value = function(){
    var val;
    val = jQuery('.form_row.field-' + this.name + ' input').val();
    if(typeof(val) == 'undefined'){
      val = jQuery('.form_row.field-' + this.name + ' textarea').val();
    }
    if(typeof(val) == 'undefined'){
      val = jQuery('.form_row.field-' + this.name + ' select option:selected').val();
    }
    return val;
  }

  this.get_value_text = function(){
    var val;
    val = jQuery('.form_row.field-' + this.name + ' input').val();
    if(typeof(val) == 'undefined'){
      val = jQuery('.form_row.field-' + this.name + ' textarea').val();
    }
    if(typeof(val) == 'undefined'){
      val = jQuery('.form_row.field-' + this.name + ' select option:selected').val();
    }
    return val;
  }

  this.add_option = function (option_key, option_value){
    this.options.push({
      key: option_key,
      value: option_value
    });
    jQuery('.form_row.field-' + this.name + ' select')
      .append("<option value=\"" + option_key + "\">" + option_value + "</option>")
    var option_id = this.name + '_' + option_key;
    jQuery('.form_row.field-' + this.name + ' .radio_group')
      .append("<div class=\"radio_group_option\"><input name=\"" + this.name + "\" id=\"" + option_id + "\" type=\"radio\" value=\"" + option_key + "\"><label for=\"" + option_id + "\">" + option_value + "</label></div>");
    return this;
  };

  this.empty = function(){
    this.options = [];
    jQuery('.form_row.field-' + this.name + ' select option').remove();
    jQuery('.form_row.field-' + this.name + ' .radio_group .radio_group_option').remove();
    return this;
  };

  this.on_change = function(callback){
    this.
      _get_input_field()
        .unbind('change')
        .bind('change', callback);
    return this;
  };

  this.disable = function(){
    this.disabled = true;
    this._get_input_field().attr('disabled', 'disabled').addClass('disabled');
    return this;
  }

  this.enable = function(){
    this.disabled = false;
    this._get_input_field().removeAttr('disabled').removeClass('disabled');
    return this;
  }

  this.html = function(){
    if(this.type == 'input'){
      return '' +
        '<div class="form_row form_input field-' + this.name + '">' +
        '  <label for="' + this.name + '">' + this.label + '</label>' +
        '  <div class="widget">' +
        '    <input type="text" placeholder="' + this.value + '" class="' + (this.disabled?'disabled':'enabled') + '" value="' + this.value + '" name="' + this.name + '" id="' + this.name + '" ' + (this.disabled?'disabled="disabled"':'') + '>' +
        '  </div>' +
        '  <div class="clear"></div>' +
        '</div>';
    }else if(this.type == 'textarea'){
      return '' +
        '<div class="form_row form_textarea field-' + this.name + '">' +
        '  <label for="' + this.name + '">' + this.label + '</label>' +
        '  <div class="widget">' +
        '    <textarea type="text" class="' + (this.disabled?'disabled':'enabled') + '" name="' + this.name + '" id="' + this.name + '" ' + (this.disabled?'disabled="disabled"':'') + '>' + this.value + '</textarea>' +
        '  </div>' +
        '  <div class="clear"></div>' +
      '</div>';
    }else if(this.type == 'select'){
      return '' +
        '<div class="form_row form_select field-' + this.name + '">' +
        '  <label for="' + this.name + '">' + this.label + '</label>' +
        '  <div class="widget">' +
        '    <select class="' + (this.disabled?'disabled':'enabled') + '" name="' + this.name + '" id="' + this.name + '" ' + (this.disabled?'disabled="disabled"':'') + '>' + this.html_select_options() + '</select>' +
        '  </div>' +
        '  <div class="clear"></div>' +
        '</div>';
    }else if(this.type == 'radio'){
      return '' +
        '<div class="form_row form_radio field-' + this.name + '">' +
        '  <div class="radio_group">' +
        this.html_radio_options() +
        '    <div class="clear"></div>' +
        '  </div>' +
        '</div>';
    }else if(this.type == 'submit'){
      return '' +
        '<div class="form_row form_submit field-' + this.name + '">' +
        '  <div class="widget">' +
        '    <input type="submit" class="' + (this.disabled?'disabled':'enabled') + '" name="' + this.name + '" id="' + this.name + '" value="' + this.label + '"/ ' + (this.disabled?'disabled="disabled"':'') + '>' +
        '  </div>' +
        '  <div class="clear"></div>' +
        '</div>';
    }else if(this.type == 'hidden'){
      return '' +
        '<div class="form_row form_hidden field-' + this.name + '">' +
        '    <input type="hidden" value="' + this.value + '" name="' + this.name + '" id="' + this.name + '">' +
        '</div>';
    }else{
      return 'Unsupported type: ' + this.type;
    }
  };

  this.html_select_options = function(){
    var option;
    var option_html = '';
    while(option = this.options.shift()){
      option_html += "<option value=\"" + option.key + "\">" + option.value + "</option>";
    }
    return option_html;
  };

  this.html_radio_options = function(){
    var radio;
    var radio_html = '';
    while(radio = this.options.shift()){
      var name = this.name + "_" +  radio.key;
      radio_html += "<div class=\"radio_group_option\">";
      radio_html += "  <input name=\"" + this.name + "\" id=\"" + name + "\" type=\"radio\" value=\"" + radio.key + '" ' + (this.disabled?'disabled="disabled"':'') + '>';
      radio_html += "  <label for=\"" + name + "\"></label>" + radio.value + "</label>";
      radio_html += "</div>";
    }
    return radio_html;
  };

  this.attach = function(event, callback){
    this.events[event] = callback;
  }

  this.rebind = function(){
    jQuery.each(this.events, function(event, callback){
      this._get_input_field().unbind(event).bind(event, callback);
    });
  }

}

function magic_form_group(name, label) {
  this.name = name;
  this.label = label;
  this.fields = [];
  this.add_field = function(field){
    this.fields.push(field);
    return this;
  };
  this.html = function(){
    return '' +
      '<div class="form_group field-' + this.name + '">' +
      '<h3>' + this.label + '</h3>' +
      '<div class="group-inside">' + this.get_fields_html() + '</div>' +
      '</div>'

  };
  this.get_fields_html = function(){
    var html = '';
    var field;
    while(field = this.fields.shift()){
      html += field.html();
    }
    return html;
  };
}

var magic_form = {
  name: '',
  label: '',
  value: '',
  form_input:  function(name, label, value){
    if(typeof(value) == 'undefined'){
      value = '';
    }
    this.name = name;
    this.label = label;
    this.value = value;
    return this;
  },
  form_group: function(name, label){
    return new magic_form_group(name, label);
  }

}