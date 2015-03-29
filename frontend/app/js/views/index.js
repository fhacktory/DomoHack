define([ "backbone", "underscore", "views/list" ],
function(Backbone, _, ListView) {
	var IndexView = Backbone.View.extend({
		el : $("#content"),
		initialize : function() {
			this.render();
		},
		render: function(){
			$(this.el).append(new ListView);
		},
	});
	return IndexView;
});