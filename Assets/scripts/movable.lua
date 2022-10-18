speed = 10
deltaVel = 0
entity = world:getEntity(entityId)
velocity = entity:getVelocity()

if input:getState():test(Direction.Left) then
    deltaVel = deltaVel - speed
end
if input:getState():test(Direction.Right) then
    deltaVel = deltaVel + speed
end

velocity.x = velocity.x + deltaVel * entity:getDeltaTime()
