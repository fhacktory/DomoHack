define([ "backbone", "widget" ], 
function(Backbone, Widget) {
	var WidgetCollection = Backbone.Collection.extend({
		model: Widget,
		url : "/rest/list",
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