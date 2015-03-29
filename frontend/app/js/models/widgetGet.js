define([ "backbone"], 
function(Backbone) {
	var WidgetGet = Backbone.Collection.extend({
		url: false,
		initialize: function(models, options) {
		    this.url = "/rest/"+options.key;
		},
		sync: function(method, model, options) {
            var params = _.extend({
                type: 'GET',
                dataType: 'json',
                url: this.url,
                processData: false,
            }, options);
            return $.ajax(params);
        }
	});
	return WidgetGet;
});