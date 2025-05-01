window.MathJax = {
  tex: {
    inlineMath: [["\\(", "\\)"]],
    displayMath: [["\\[", "\\]"]],
    processEscapes: true,
    processEnvironments: true
  },
  options: {
    ignoreHtmlClass: ".*|",
    processHtmlClass: "arithmatex"
  }
};

document$.subscribe(() => {
  MathJax.typesetPromise()
})

/*
window.onload = function() {
   let msform1 = document.getElementById("msform1");
   let doc = msform1.contentDocument;
   doc.body.innerHTML = doc.body.innerHTML + '<style>div.__title__.office-form-form-title.office-form-theme-primary-background.office-form-title-container{padding:5px !important;}</style>';
}
*/
