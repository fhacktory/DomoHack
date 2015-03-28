define([ "backbone" ],
function(Backbone) {
	var IndexView = Backbone.View.extend({
		el : "body",
		initialize : function() {
			this.render();
		},
		render: function(){
			$(this.el).append("<h1>Hello world</h1>");
		},
	});
	return IndexView;
});