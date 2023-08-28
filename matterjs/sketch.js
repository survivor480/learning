var Engine = Matter.Engine,
Render = Matter.Render,
Runner = Matter.Runner,
World = Matter.World,
Bodies = Matter.Bodies


var engine;
var world;
var boxes = [];
var ground;

function setup() {
  createCanvas(400, 400);
  engine = Engine.create();
  world = engine.world;
  Runner.run(engine);
  var options = {
    isStatic: true
  };
  ground = Bodies.rectangle(200, height - 50, width, 10, options);
  World.add(world, ground);
  console.log(ground);
}

function mouseDragged() {
  boxes.push(new Box(mouseX, mouseY, 20, 20));
}

function draw() {
  background(51);
  for(var i=0; i<boxes.length; i++){
    boxes[i].show();
  }

  noStroke(255);
  fill(255);
  rectMode(CENTER);
  // strokeWeight(4);
  rect(ground.position.x, ground.position.y, width, 10);
}
