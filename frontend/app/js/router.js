define([ "backbone", "views/index", "views/widget"], 
function(Backbone, IndexView, Widget) {
	var AppRouter = Backbone.Router.extend({
		routes : {
			'widgetlist' : 'widgetlist',
			'*actions' : 'defaultAction',
		}
	});
	var initialize = function() {
		var router = new AppRouter();
		
		router.on('route:defaultAction', function() {
			new IndexView();
		});
		
		router.on('route:widgetlist', function() {
			new Widget();
		});
		
		Backbone.history.start();
	};
	return {
		initialize : initialize
	};
});