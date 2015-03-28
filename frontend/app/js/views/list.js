define([ "backbone" ],
function(Backbone) {
	var ListView = Backbone.View.extend({
		el : "body",
		initialize : function() {
			this.render();
		},
		render: function(){
			$(this.el).append("<h1>my view list</h1>");
		},
	});
	return ListView;
});