define([ "backbone"], 
function(Backbone) {
	var WidgetGet = Backbone.Collection.extend({
		url: false,
		initialize: function(models, options) {
		    this.url = "http://192.168.3.218:5000/rest/"+options.key;
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