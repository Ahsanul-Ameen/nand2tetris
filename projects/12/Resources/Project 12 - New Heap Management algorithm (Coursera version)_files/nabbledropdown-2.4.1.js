var dropdownItems = [];
var $visibleSubmenu = null;
var INTERVAL = null;

var itemColor;
function getItemColor() {
	if (!itemColor)
		itemColor = $('span.dropdown-item').css('color');
	return itemColor;
};

function closeDropdowns() {
	for (var i = 0; i < dropdownItems.length; i++) {
		var span = $('#'+dropdownItems[i]);
		$('table,ul', span).fadeOut("fast");
	}
	$('ul.dropdown-submenu').fadeOut("fast");
	clearTimeout(INTERVAL);
	$visibleSubmenu = null;
};

function dropdownUpdateLink(columnId) {
	var row = $('#'+columnId).parent().get();
	_update(row);
};

function _update(row, checkdone) {
	var $row = $(row);
	if ($row.attr('done') && checkdone)
		return;
	var submenu = $row.attr('submenu')? '<img class="submenu" src="/images/submenu.gif" width=8 height=13 style="float:right;margin-top:.3em"/>':null;

	var $link = $('a', row);
	$link.wrapInner('<span class="dropdown-item"></span>');
	if ($link && !$link.attr('ignore')) {
		if (submenu) {
			$link.css({display:'block',marginRight:'1em'}).parent().prepend(submenu);
		} else {
			$link
				.css('width', '100%')
				.css('display','block')
				.css('color', getItemColor());
		}
	}
	$row.attr('done','y');
};

function dropdownCleanup(id) {
	$('#'+id).unbind().removeAttr('init');
};

function dropdownClick(o) {
	var $this = $(this);
	var id = $this.attr('id');
	if (!$this.attr('init')) {
		firstTime(id);
		$this.attr('init', '1');
	}
	var submenu = $(o.target).parents('tr').attr('submenu');
	if (submenu) {
		o.stopPropagation();
		return;
	}
	var $t = $('table', this);
	closeDropdowns();
	if (!$t.is(':visible')) {
		var $link = $t.siblings().first();
		var off = $link.offset();
		var w = $(window).width();
		var left = off.left;
		var top = off.top + $link.outerHeight();
		if (left + $t.outerWidth() > w) {
			left = w - $t.outerWidth() - 10;
		}
		$t.css({ left: left,  top: top});
		$t.show(function() {
			if (left + $t.outerWidth() > w) {
				left = w - $t.outerWidth() - 10;
				$t.css('left', left);
			}
		});
	}
};

function dropdownInit(id) {
	var $drop = $('#'+id);
	$drop.unbind().click(dropdownClick);
};

function firstTime(id) {
	var $drop = $('#'+id);
	dropdownItems.push(id);
	var $t = $('table', $drop);
	var colorNormal = null;
	var colorSelected = null;

	var $tr = $('tr', $drop);
	$tr.each(function() {
		if ($(this).hasClass('dropdown-separator'))
			return;
		_update(this);
		var $row = $(this);

		var submenuId = $(this).attr('submenu');
		var $submenu = submenuId? $('#'+submenuId) : null;

		if ($submenu) {
			$('a', $submenu)
				.css('display','block')
				.css('width', '100%')
				.css('color', getItemColor())
				.wrapInner('<span class="dropdown-item"/>');

			$('li',$submenu).hover(
				function(e) {
					if (colorSelected) $(this).css('background-color',colorSelected);
					clearTimeout(INTERVAL);
					e.stopPropagation();
				},
				function(e) {
					if (colorNormal) $(this).css('background-color',colorNormal);
					e.stopPropagation();
				}
			);
		}

		function handleSubmenu() {
			clearTimeout(INTERVAL);
			if ($submenu)
				INTERVAL = setTimeout(openSubmenu, 400);
			else
				INTERVAL = setTimeout(closeSubmenu, 600);
		};

		function openSubmenu() {
			if ($visibleSubmenu == $submenu)
				return;
			closeSubmenu();
			$submenu.css('background-color',$t.css('background-color'));
			var rh = $row.outerHeight();
			rh = rh % 2 == 0? rh : rh-1;
			var top = $row.offset().top - rh/2;
			var left = $t.offset().left + $t.outerWidth();
			if ($submenu.outerWidth() + left > $(window).width() - 20) {
				left = $t.offset().left - $submenu.outerWidth();
				left = left < 0? 0 : left;
			}
			$submenu.css({top:top,left:left});
			$submenu.fadeIn('fast');
			$visibleSubmenu = $submenu;
		};

		function closeSubmenu() {
			if ($visibleSubmenu)
				$visibleSubmenu.fadeOut();
			$visibleSubmenu = null;
		};

		$(this).hover(
			function(e) {
				$(this).addClass('dark-bg-color');
				if (!colorSelected) colorSelected = $(this).css('background-color');
				handleSubmenu();
				e.stopPropagation();
			},
			function(e) {
				$(this).removeClass('dark-bg-color');
				if (!colorNormal) colorNormal = $(this).css('background-color');
				e.stopPropagation();
			}
		);
	});
	NabbleDropdown.showSeparators($tr.get(0));
};

$(document).ready(function() {
	$(document).click(function(o){
		var $tg = $(o.target);
		var parents = $tg.parents('.dropdown');
		if (parents.size() == 0 && !$tg.hasClass('dropdown'))
			closeDropdowns();
	});
});

/* Dropdown builder */

function NabbleDropdown(id,linkText,linkTitle) {
	this.id = id;
	this.text = linkText;
	this.title = linkTitle;
	this.options = [];
	this.submenus= [];
	this.groupCounter = 0;
	this.built = false;
};

NabbleDropdown.prototype.customButton = function(element) {
	this.element = element;
};

NabbleDropdown.prototype.add = function(id,contents,style) {
	var o = {id:id,contents:contents,style:style};
	if (this.currentGroup) {
		var lastGroup = this.submenus.length == 0? null : this.submenus[this.submenus.length-1];
		if (lastGroup == null || lastGroup.id != this.currentGroup) {
			lastGroup = {id:this.currentGroup, options: []};
			this.submenus.push(lastGroup);
		}
		lastGroup.options.push(o);
	} else
		this.options.push(o);
};

NabbleDropdown.prototype.addSeparator = function() {
	this.options.push('separator');
};

NabbleDropdown.prototype.startGroup = function(text) {
	this.currentGroup = 'sm'+this.groupCounter;
	this.options.push({id:this.currentGroup+'-id',contents:"<a href=\"javascript:void(0)\">"+text+"</a>",style:"display:none",submenu:this.currentGroup});
	this.groupCounter++;
};

NabbleDropdown.prototype.endGroup = function() {
	this.currentGroup = null;
};

NabbleDropdown.prototype.addCustomSubmenu = function(text, boxId) {
	this.options.push({id:boxId+'-id',contents:"<a href=\"javascript:void(0)\">"+text+"</a>",submenu:boxId});
	this.currentGroup = null;
};

NabbleDropdown.prototype.getHtml = function() {
	var html = '<span id="'+this.id+'" class="dropdown">';
	if (this.element)
		html += this.element;
	else {
		html += '<a href="javascript:void(0)"' + (this.title?' title="'+this.title+'"':'') + '>'+this.text+'</a> ';
		html += '<img src="/images/more.png" width="10" height="10"/>';
	}
	html += '<table class="light-bg-color medium-border-color drop-shadow" style="margin-top:1px;">';
	html += '<tr id="_loading' +this.id+'" style="display:none"><td class="dropdown-simple-row"><span id="_loadingSpan'+this.id+'">Loading...</span></td></tr>';
	for (var i=0; i<this.options.length;i++) {
		var x = this.options[i];
		if (x == 'separator') {
			html += '<tr class="dropdown-separator"><td class="action-separator medium-border-color">&nbsp;</td></tr>';
		} else {
			html += '<tr';
			if (x.id) html += ' id="'+x.id+'"';
			if (x.style) html += ' style="'+x.style+'"';
			if (x.submenu) html += ' submenu="'+x.submenu+'"';
			html += '><td style="border:none">'+x.contents+'</td></tr>';
		}
	}
	html += '</table>';
	for (var i=0;i<this.submenus.length;i++) {
		var x = this.submenus[i];
		html += '<ul id="'+x.id+'" class="light-bg-color medium-border-color drop-shadow">';
		for (var j=0;j<x.options.length;j++) {
			var y = x.options[j];
			html += '<li';
			if (y.id) html += ' id="'+y.id+'"';
			if (y.style) html += ' style="'+y.style+'"';
			html += '>'+y.contents+'</li>';
		}
		html += '</ul>';
	}
	html += '</span>';
	return html;
};

NabbleDropdown.prototype.build = function(elemId) {
	$('#'+elemId).html(this.getHtml());
	dropdownInit(this.id);
};

NabbleDropdown.prototype.loadingAnimation = function(id,action) {
	var $span = $('#_loadingSpan'+id);
	if (action == 'start') {
		NabbleDropdown.show('_loading'+id);
		function loading1() { $span.fadeTo(300,0.3,loading2);  };
		function loading2() { $span.fadeTo(300,1,loading1);  };
		loading1();
	} else {
		NabbleDropdown.hide('_loading'+id);
		$span.stop();
	}
};

NabbleDropdown.prototype.loadOnClick = function(scriptUrl) {
	var _this = this;
	var id = this.id;
	var hasRequested = false;
	var $drop = $('#'+this.id);
	$drop.mouseover(function() {
		if (!hasRequested) {
			hasRequested = true;
			_this.loadingAnimation(id, 'start');
			$.getScript(scriptUrl, function() {
				_this.loadingAnimation(id, 'stop');
			});
		}
	});
};

NabbleDropdown.show = function(id) {
	var e = document.getElementById(id);
	if (e.nodeName == 'LI') {
		e.style.display = 'list-item';
		var p = document.getElementById(e.parentNode['id']+'-id');
		p.style.display = $.browser.msie?'block':'table-row';
		NabbleDropdown.showSeparators(p);
	} else {
		e.style.display = $.browser.msie?'block':'table-row';
		NabbleDropdown.showSeparators(e);
	}
};

NabbleDropdown.hide = function(id) {
	var e = document.getElementById(id);
	e.style.display = 'none';
	NabbleDropdown.showSeparators(e);
};

NabbleDropdown.showSeparators = function(e) {
	while (e.previousSibling)
		e = e.previousSibling;
	var separators = [];
	while (e) {
		if (e.nodeName != 'TR') return;
		if (e.className == 'dropdown-separator')
			separators.push(e);
		else if (e.style.display != 'none')
			separators.push('X');
		e = e.nextSibling;
	}
	for (var i=0; i<separators.length;i++) {
		if (typeof separators[i] != 'string') {
			var prev = i > 0 && separators[i-1] == 'X';
			var next = i < separators.length-1 && separators[i+1] == 'X';
			if (next && prev) {
				separators[i].style.display = $.browser.msie?'block':'table-row';
			}
		}
	}
};

NabbleDropdown.addContents = function(id,contents) {
	var $row = $('#'+id);
	$row.html('<td>'+contents+'</td>').show();
	_update($row.get(),false);
};

NabbleDropdown.replaceContents = function(id,contents) {
	$('#'+id).html('<td class="dropdown-simple-row">'+contents+'</td>');
};