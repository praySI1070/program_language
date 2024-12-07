const { createProxyMiddleware } = require('http-proxy-middleware');
const REACT_APP_API_URL = process.env.REACT_APP_API_URL;


module.exports = function(app) {
    app.use(
        createProxyMiddleware("/", {
            target:`http://${REACT_APP_API_URL}`,
            changeOrigin:true,
        })
    )
}