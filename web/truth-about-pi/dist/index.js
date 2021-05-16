const Koa = require('koa');
const get = require('lodash.get');
const bodyParser = require('koa-bodyparser')

const app = new Koa()
app.use(bodyParser({enableTypes: ['form']}))

app.use(async (ctx) => {
	let content = '';
	if (ctx.method === 'POST') {
		const {index} = ctx.request.body;
		const pi = Math.PI.toString();
		const digit = parseInt(get(pi, index));
		content = `
			<h1>円周率の${index}桁目は${digit}です！</h1>
			${digit === 0 ? `<p>${process.env.FLAG}</p>` : ''}
		`;
	}

	ctx.body = `
		<!DOCTYPE html>
		<title>円周率に関する真実をお伝えします</title>
		<body style="text-align: center">
			<h1>円周率には0が出現しないって知っていますか?</h1>
			<p>論より証拠、試してみてください!</p>
			${content}
			<form method="POST">
				円周率の<input type="number" name="index">桁目は?
				<input type="submit">
			</form>
		</body>
	`;
});

app.listen(3000);

