using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class 子弹控制 : MonoBehaviour
{
    Rigidbody2D rbody;

    public AudioClip hitClip;

    // Start is called before the first frame update
    void Awake()
    {
        rbody = GetComponent<Rigidbody2D>();
        Destroy(this.gameObject, 2f);//2秒后自动消失
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    //子弹移动
    public void Move(Vector2 moveDirection, float moveForce){
        rbody.AddForce(moveDirection * moveForce);
    }

    //子弹消失
    void OnCollisionEnter2D(Collision2D other){
        敌人 ec = other.gameObject.GetComponent<敌人>();
        if(ec != null){
            Debug.Log("子弹碰到敌人了~");
            ec.Fixed();
        }
        AudioManager.instance.AudioPlay(hitClip);
        Destroy(this.gameObject);
    }
}
