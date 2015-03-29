define([ "backbone", "underscore", "views/widget" ],
function(Backbone, _, Widget) {
	var IndexView = Backbone.View.extend({
		el : $("#select-content"),
		initialize : function() {
			this.render();
		},
		render: function(){
			$(this.el).append(new Widget);
		},
	});
	return IndexView;
});