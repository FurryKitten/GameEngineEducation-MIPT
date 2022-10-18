deltaVel = 0.0
bouncePlane = { x = 0, y = 1, z = 0, w = 0 }
planeEpsilon = 0.1;
jumpSpeed = 10;

entity = world:getEntity(entityId)
velocity = entity:getVelocity()
pos = entity:getPosition()


if bouncePlane.x*pos.x + bouncePlane.y*pos.y + bouncePlane.z*pos.z < bouncePlane.w + planeEpsilon then
    if input:getState():test(Direction.Jump) then
        velocity.y = jumpSpeed
    end
end
