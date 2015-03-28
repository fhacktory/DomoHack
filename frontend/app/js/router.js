define([ "backbone", "views/index", "service" ], function(Backbone, IndexView, Service) {
	var AppRouter = Backbone.Router.extend({
		routes : {
			'list' : 'list',
			'*actions' : 'defaultAction',
		}
	});
	var initialize = function() {
		var router = new AppRouter();
		
		router.on('route:defaultAction', function() {
			new IndexView();
		});
		
		router.on('route:list', function() {
			console.log(Service);
			var service =  new Service();
			/*Service.set({"type": "list"});
			console.log(Service.get('type'));
			/*require([ 'views/optimize/page' ], function(OptimizePage) {
				var optimizePage = Vm.create(appView, 'OptimizePage',
						OptimizePage);
				optimizePage.render();
			});*/
			console.log('dede');
			alert('dede');
		});
		Backbone.history.start();
	};
	return {
		initialize : initialize
	};
});