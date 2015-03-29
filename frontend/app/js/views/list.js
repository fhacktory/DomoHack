define([ "backbone", "underscore", "widget", "models/widgetCollection" ],
function(Backbone, _, Widget, WidgetCollection) {
	var ListView = Backbone.View.extend({
		el : $("#content"),
		initialize : function() {
			this.widgetCollection = new WidgetCollection;
			var that = this;
			this.widgetCollection.fetch({
		        complete: function (datas) {
		        	that.render(datas);
		        }
		    });
		},
		
	    template: _.template($('#widgetCollectionTemplate').html()),

	    render: function(datas) {
	    	$(this.el).html(this.template({ "widgets": datas.responseJSON}));
	    }
	});
	return ListView;
});