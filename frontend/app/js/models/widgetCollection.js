define([ "backbone"], 
function(Backbone) {
	var WidgetCollection = Backbone.Collection.extend({
		url : "http://192.168.3.218:5000/rest/list",
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
	return WidgetCollection;
});