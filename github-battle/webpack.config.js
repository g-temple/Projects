// webpack takes all the app modules and converts them to static assets
const path = require('path')
const HtmlWebpackPlugin = require('html-webpack-plugin')

module.exports = {
    entry: "./app/index.jsx",
    output: {
        path: path.resolve(__dirname, "dist"), // after the modules are combined, put the file here
        filename: "index_bundle.js" // file name of combined modules from ^^
    },
    module: {
        rules: [ // rules for what loader webpack is supposed to do once it encounters a file type specified by the test property
            {test: /\.(js|jsx)$/, use: "babel-loader" },
            {test: /\.css$/, use: ["style-loader","css-loader"]}
        ]
    },
    resolve:{
        extensions: [".jsx", "..."] // support importing jsx files
    },
    mode: "development", // could be developement or production
    plugins: [
        new HtmlWebpackPlugin({
            template: "app/index.html" // tells where to copy the index.html of our app, so when we ship dist to github, this gets copied
        })
    ]



}