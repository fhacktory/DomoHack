define([ "backbone"], 
function(Backbone) {
	var WidgetSet = Backbone.Collection.extend({
		url: false,
		initialize: function(models, options) {
		    this.url = "/rest/"+options.key+"/"+options.commut;
		},
		sync: function(method, model, options) {
            var params = _.extend({
                type: 'PUT',
                dataType: 'json',
                url: this.url,
                processData: false,
            }, options);
            return $.ajax(params);
        }
	});
	return WidgetSet;
});