const express = require('express')
const app = express()
const cc = require('./build/Release/addon');
const cors = require('cors')

app.use(cors());
app.use(express.json());

app.get('/', (req, res) => {
  res.send(`Hello World`);
})

app.post('/geometry', (req, res) => {
  let geometries = req.body;
  console.log('This should be eight:', cc.add(3, 5));
  return res.status(200).json(geometries);
});

app.post('/add', (req, res) => {
  let num = req.body.add;
  
  return res.status(200).json({
    success: true,
    result: cc.add(num[0], num[1]),
  });
});

app.post('/triangular', (req, res) => {
  let geometries = req.body.geometries;
  let numberOfElements = req.body.numberOfElements;

  const result = cc.triangular(geometries, numberOfElements);
  console.log(result)

  return res.status(200).json({
    success: true,
    messages: 'triangulared successfully.',
    results: result
  });
});

app.listen(4000, () => console.log('Example app listening on port 4000!'))